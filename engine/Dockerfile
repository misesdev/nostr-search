
# Use the image base with gcc compiler
FROM gcc:latest

# Install dependeces
RUN apt-get update && apt-get install -y libcjson-dev && apt-get install -y libjemalloc-dev

# Create work directory
WORKDIR /usr/src/app

# Copy files to work firectory
COPY . .

# Compily the program
RUN gcc ./main.c -o ./build/nostr-find -lcjson -ljemalloc && chmod +x ./build/nostr-find

EXPOSE 8080

# Execute
CMD ["./build/nostr-find"] 


