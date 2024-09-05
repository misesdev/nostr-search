import { WebSocket } from "ws"

const author = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";
const subscription = "3da979448d9ba263864c4d6f14984c423a3838364ec255f03c7904b1ae77f206";
    
const server = new WebSocket("wss://relay.damus.io/");

server.on("open", () => {
    console.log("open connection");
    
    server.send(`[\"REQ\",\"${subscription}\",{ \"kinds\": [1], \"limit\": 3,\"authors\": [\"${author}\"]}]`);
});

server.on("message", (message) => {
    const data = JSON.parse(message.toString())

    if(data[0] == "EOSE") {
        server.close();
        return;
    }

    const event = (data[0] == "EVENT") ? data[2] : null;

    if(event)
        console.log("received event: ", event);

    console.log("\n\nreceived message:", data);

    setTimeout(() => {
        server.send(`[\"CLOSE\", \"${subscription}\"]`);
    }, 1000);
});

server.on("close", () => {
    console.log("\n\nclose connection");

});

server.on("eose", () => {
    server.close();
})

server.on("error",  (err) => {
    console.log("\n\nconnection error", err);
});



