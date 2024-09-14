import { RelayPool } from "../modules/RelayPool";
import { FileSystem } from "../filesytem/disk";

export const listUsers = async (pool: RelayPool) => {
    
    const pubkeys: string[] = []

    const fileUsers = new FileSystem("users.db");
    const filePubkeys = new FileSystem("pubkeys.db");

    await filePubkeys.readLines(async (line) => { pubkeys.push(line) })

    let skipe = 200
    for (let i = 0; i <= pubkeys.length; i += skipe) 
    {
        let authors = pubkeys.slice(i, i + skipe)

        let events = await pool.fechEvents({
            authors: authors,
            limit: skipe,
            kinds: [0]
        })

        console.log("events:", events.length);

        events.forEach(event => {
            try {
                let user = JSON.parse(event.content)
                user["pubkey"] = event.pubkey
                fileUsers.writeLine(JSON.stringify(user))
            } catch {}
        });
    }

    console.log("found users:", pubkeys.length)
}
