import { FileSystem } from "../filesytem/disk";
import { RelayPool } from "../modules/RelayPool";
import { getPubkeys } from "../utils";

export const listPubkeys = async (pool: RelayPool, author: string) => {
    
    const file = new FileSystem("pubkeys.db")

    const pubkeys: string[] = []

    file.readLines(async (pubkey) => {
        pubkeys.push(pubkey)
        return true
    })

    if(pubkeys.length <= 0) {
        const events = await pool.fechEvents({
            authors: [author],
            kinds: [3],
            limit: 1
        })

        if(events.length) 
            getPubkeys(events[0]).forEach(pubkey => pubkeys.push(pubkey))
    }

    let skipe = 150, maxPubkeys = 1079000
    for(let i = 0; i < pubkeys.length; i += skipe) 
    {
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

        if(pubkeys.length > maxPubkeys) break
    }

    await file.clear()

    pubkeys.forEach(pubkey => file.writeLine(pubkey))

    console.log("users:", pubkeys.length)
}
