type User = {
    name?: string,
    pubkey?: string,
    displayName?: string
}

const pubkey: string = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27"

const request = async (endpoint: string, data: any) => {
    const response = await fetch(`http://localhost:8080/${endpoint}`, {
        method: "post",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    })

    return await response.json()
}

const main = async () => {
    
    const friends: User[] = await request("get_friends", { pubkey }) 

    for(let i = 0; i <= 80000; i++)
    {
        try 
        {
            let user = friends[i % friends.length]
            
            console.log("user:", user.displayName)

            let results: User[] = await request("search_users", { 
                pubkey: user.pubkey, 
                searchTerm: user.displayName 
            })        

            console.log("-> results", results.length)
        }
        catch { }
    }

    console.log("friends:", friends.length)
}

main()



