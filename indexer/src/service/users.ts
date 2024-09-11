import { RelayPool } from "../modules/RelayPool";
import { FileSystem } from "../filesytem/disk";

export const listUsers = async (pool: RelayPool) => {
    
    const pubkeys: string[] = []

    const filePubkeys = new FileSystem("pubkeys.db");
    const fileUsers = new FileSystem("users.db");

    await filePubkeys.readLines(line => pubkeys.push(line))

    let skipe = 100
    for (let i = 0; i < pubkeys.length; i += skipe) {
        let authors = pubkeys.slice(i, i + skipe)

        let events = await pool.fechEvents({
            authors: authors,
            kinds:[0],
            limit: skipe
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

}
