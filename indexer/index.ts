import { Event } from "./src/modules/types";
import { RelayPool } from "./src/modules/RelayPool";
import { relays } from "./src/constants/Relays";
import { FileSystem } from "./src/filesytem/disk";
import { getPubkeys } from "./src/utils";

const author: string = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";

const main = async () => {

    let fileUsers = new FileSystem("./data/users.db");
    let filePubkeys = new FileSystem("./data/pubkeys.db");

    const pool = new RelayPool(relays);

    await pool.connect();

    let userEvent = await pool.fechUser(author);
    let pubkeys: string[] = getPubkeys(userEvent);
    pubkeys.push(userEvent.pubkey);

    let skip = 10;
    for(let i = 0; pubkeys.length < 20000; i += skip) {
        let events = await pool.fechEvent({
            authors: pubkeys.slice(i, i + skip),
            kinds: [3],
            limit: skip
        });
        if(events.length > 0) 
        {
            events.forEach(event => {               
                console.log(`${event.tags.length} follows:`, event.pubkey.substring(0, 15))
                
                let npubs = getPubkeys(event).filter(npub => !pubkeys.includes(npub))
                
                npubs.forEach(pub => pubkeys.push(pub))
            })
        } else 
            console.log("not found")

        skip++;
    }

    pubkeys.forEach(pubkey => filePubkeys.writeLine(pubkey));

    skip = 100;
    for(let i = 0; i < pubkeys.length; i += skip) {
        let events = await pool.fechEvent({
            authors: pubkeys.slice(i, i + skip),
            kinds: [0],
            limit: skip
        })
        if(events.length > 0) {
            console.log("found users:", events.length)
            events.forEach(event => fileUsers.writeLine(event.content))
        } else
            console.log("not found users")
    } 

    console.log("found users from nostr:", pubkeys.length);
}

main();


