import { RelayPool } from "../modules/RelayPool";
import { FileSystem } from "../filesytem/disk";
import { UserFriends } from "../modules/types";
import { getPubkeys } from "../utils";

export const listFriends = async (pool: RelayPool) =>
{
    const fileFriends = new FileSystem("./data/friends.db")
    const filePubkeys = new FileSystem("./data/pubkeys.db")

    const pubkeys: string[] = []
    const usersFriends: UserFriends[] = [] 

    await filePubkeys.readLines(async (pubkey) => {
        pubkeys.push(pubkey)
        return true
    })

    let skipe = 300
    for(let i = 0; i < pubkeys.length; i += skipe) 
    {
        let events = await pool.fechEvents({
            authors: pubkeys.slice(i, i + skipe),
            limit: skipe,
            kinds: [3]
        })

        if(events.length) 
        {
            events.forEach(event => {
                let npubs = getPubkeys(event)
                console.log("npubs:", npubs.length)
                let user: UserFriends = {
                    pubkey: event.pubkey,
                    friends: []
                }
                user.friends = npubs.map(npub => pubkeys.indexOf(npub))
                usersFriends.push(user)
            })
        }
    }

    usersFriends.forEach(user => {
        let friends = JSON.stringify(user)
        fileFriends.writeLine(friends)
    })

    console.log("loaded friends:", usersFriends.length);
    console.log("pubkeys:", pubkeys.length);
}
