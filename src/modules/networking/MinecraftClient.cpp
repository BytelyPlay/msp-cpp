module;

module MinecraftClient;

// PUBLIC
std::shared_ptr<MinecraftClient> MinecraftClient::create(tcp::socket& socket)
{
    return std::make_shared<MinecraftClient>
    (socket);
}

// PRIVATE
MinecraftClient::MinecraftClient(tcp::socket& socket) : socket(socket)
{

}

void MinecraftClient::write(char* bytes, size_t amount)
{

}
