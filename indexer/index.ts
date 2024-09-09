import { Event } from "./src/modules/types";
import { RelayPool } from "./src/modules/RelayPool";
import { relays } from "./src/constants/Relays";
import { FileSystem } from "./src/filesytem/disk";
import { getPubkeys } from "./src/utils";

const author: string = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";

const main = async () => {

    let pubkeys: string[] = [author];

    let file = new FileSystem("pubkeys.db");

    const pool = new RelayPool(relays, author);

    await pool.connect();

    //let user = await pool.fetchUser(author);

    //pubkeys.push(user.pubkey)

    ///file.writeLine(nostrEvent.content)

    let key = 0;
    while(pool.pubkeys.length < 5000) {
        console.log("search event from key", pool.pubkeys[key]);
        await pool.fechEvent({
            authors: [pool.pubkeys[key]],
            kinds: [3],
            limit: 1
        });

        //let npubs = getPubkeys(events[0]).filter(f => !pubkeys.includes(f))
        
        //console.log("npubs", npubs.length)

        //npubs.forEach(pub => pubkeys.push(pub));
        //pubkeys = [...pubkeys, ...npubs];

        key++;
    }

    pool.pubkeys.forEach(pubkey => file.writeLine(pubkey));

    console.log("found users from nostr:", pool.pubkeys.length);
}

main();


