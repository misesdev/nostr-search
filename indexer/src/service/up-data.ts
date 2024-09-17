import { FileSystem  } from "../filesytem/disk";
import { User, UserFriends } from "../modules/types";

export const loadData = async () => {
    
    const pubkeys: string[] = []
    const fileUsers = new FileSystem("./data/users.db")
    const fileFriends = new FileSystem("./data/friends.db")
    const filePubkeys = new FileSystem("./data/pubkeys.db")

    await filePubkeys.readLines(async (pubkey) => {
        pubkeys.push(pubkey)
        return true
    })

    // send users
    await fileUsers.readLines(async (line) => {
        
        return await new Promise(async (resolve) => {
            let response = await fetch("http://localhost:8080/add_user", {
                method: "post",
                body: line,
            })
            
            let data = await response.json()
            console.log(data.message)

            if(!response.ok) console.log(data)

            setTimeout(() => resolve(true), 50)
        })
    })

    let response = await fetch("http://localhost:8080/save", {
        method: "post"
    })

    let data = await response.json()

    console.log(data.message)

    // send friends
    await fileFriends.readLines(async (line) => {
        
        return await new Promise(async (resolve) => {

            let friends: string[] = []
            let userFriends: UserFriends = JSON.parse(line);
            
            let user: User = { 
                pubkey: userFriends.pubkey,
                friends: []
            }
            
            userFriends.friends.forEach(index => {
                let pubkey = pubkeys[index]
                if(pubkey) 
                    friends.push(pubkey)
            })

            let interval = 150
            for(let i = 0; i < friends.length; i += interval) 
            {
                user.friends = friends.slice(i, i + interval)

                let response = await fetch("http://localhost:8080/add_friends", {
                    method: "post",
                    body: JSON.stringify(user)
                })

                let data = await response.json()
                
                if(!response.ok) console.log(user)

                console.log(data.message)
            }

            setTimeout(() => resolve(true), 100)
        })
    })

    response = await fetch("http://localhost:8080/save", {
        method: "post"
    })

    data = await response.json()

    console.log(data.message)
}




