# What is this?
This is a Minecraft server protocol implementation in C++. \
Using Boost.ASIO. \
This library's goal is simply to implement every single Minecraft packet and make it easy to send and receive packets. \
This way in the future if anyone would like to they can try to recreate the Minecraft server in C++ easily. \
The goal is to make packet sending 100% thread-safe, make this multi-threaded \
and having decent-ish performance \ 
(although performance will highly depend on your code's quality).

# Build instructions
On Ubuntu (and likely other debian-based distributions):
1. Make sure the apt package libboost-all-dev is installed and openssl
2. clone this repo
3. TODO

# Current Version
It is not yet versioned since it is in the very early development phase. \
It should target Minecraft 1.21.10 \ 
(for now, once I can get documentation for a newer version, I'll jump on it)

# Packets with predefined listeners
1. C2SLoginStartPacket
2. C2SIntentionPacket

# Credits
https://minecraft.wiki/w/Java_Edition_protocol/Packets for the spec, \
and helping me understand how Minecraft encodes VarInts \
(A.K.A. The exact same way as the standard).