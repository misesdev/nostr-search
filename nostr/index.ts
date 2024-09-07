import { Event } from "./src/modules/types";
import { RelayPool } from "./src/modules/RelayPool";

const relays: string[] = [
    "wss://relay.damus.io",
    "wss://relay.nostr.bg",
    "wss://nostr.bitcoiner.social",
];
const author: string = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";

const main = async () => {

    let events: Event[];

    const pool = new RelayPool(relays);

    await pool.connect();

    events = await pool.fechEvent({ 
        authors: [author], 
        kinds:[1], 
        limit: 5 
    });

    console.log(events);
}

main();


