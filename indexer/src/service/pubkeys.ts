import { FileSystem } from "../filesytem/disk";
import { RelayPool } from "../modules/RelayPool";
import { getPubkeys } from "../utils";

export const listPubkeys = async (pool: RelayPool, author: string, userCount: number) => {
    
    const file = new FileSystem("pubkeys.db")

    const events = await pool.fechEvents({
        authors: [author],
        kinds: [3],
        limit: 1
    })

    if(events.length) {
        const pubkeys: string[] = getPubkeys(events[0])

        let skipe = 50;
        for(let i = 0; pubkeys.length < userCount; i += skipe) {
            let authors = pubkeys.slice(i, i + skipe)
            
            let events = await pool.fechEvents({
                authors: authors,
                kinds: [3],
                limit: skipe
            })
            
            events.forEach(event => {
                let npubs = getPubkeys(event)
                console.log("npubs", npubs.length)
                npubs.forEach(pubkey => { 
                    if(!pubkeys.includes(pubkey))
                        pubkeys.push(pubkey)
                })
            })
        }

        pubkeys.forEach(pubkey => file.writeLine(pubkey))

        console.log("users:", pubkeys.length)
    }
}
