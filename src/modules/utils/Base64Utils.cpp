module;
#include <complex>
#include <stdexcept>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <vector>
#include <openssl/err.h>

module Base64Utils;
import Logger;

std::string Base64Utils::encode(std::vector<unsigned char> bytes, bool& success)
{
    std::vector<unsigned char>
    base64String(4 * ((bytes.size() + 2) / 3));

    BIO *bio, *b64;
    int readCode;

    bio = BIO_new(BIO_s_mem());
    b64 = BIO_new(BIO_f_base64());

    if (!bio) goto err;
    if (!b64) goto err;

    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    b64 = BIO_push(b64, bio);
    if (
        BIO_write(b64,
        bytes.data(),
        bytes.size()) <= 0
    ) goto err;
    if (BIO_flush(b64) <= 0) goto err;

    readCode = BIO_read(bio, base64String.data(), base64String.size());
    if (readCode <= 0)
    {
        success = false;
        Logger::warn("No data has been written to vector for base64");

        goto err;
    }

    BIO_free_all(b64);

    success = true;
    return { base64String.begin(), base64String.end() };

    err:
    Logger::warn("Couldn't encode Base64");
    success = false;

    if (b64) BIO_free(b64);
    if (bio) BIO_free(bio);

    return "";
}
std::vector<unsigned char> Base64Utils::decode(std::string base64, bool& success)
{
    BIO *bio, *b64;
    int padding;

    size_t expectedSize;

    std::vector<unsigned char> data;

    bio = BIO_new(BIO_s_mem());
    b64 = BIO_new(BIO_f_base64());

    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    b64 = BIO_push(b64, bio);

    if (BIO_write(bio, base64.data(), base64.size()) <= 0) goto err;

    padding = -1;
    for (int i = 0; i < 4; i++)
    {
        if (base64[base64.size() - i - 1] == '=') continue;
        padding = i;
        break;
    }
    if (padding == -1)
    {
        Logger::warn("Something went wrong, "
                     "couldn't detect amount of padding in base64 string");
        goto err;
    }
    expectedSize = (base64.size() / 4) * 3 - padding;
    data.resize(expectedSize);

    if (BIO_read(b64, data.data(), data.size()) <= 0) goto err;

    BIO_free_all(b64);

    success = true;

    return data;

    err:
    Logger::warn("Couldn't decode Base64");

    unsigned long err;
    char errMsg[1024];

    while ((err = ERR_get_error()) != 0)
    {
        ERR_error_string_n(err, errMsg, sizeof(errMsg));
        Logger::warn(errMsg);
    }
    success = false;

    if (b64) BIO_free(b64);
    if (bio) BIO_free(bio);

    return {};
}