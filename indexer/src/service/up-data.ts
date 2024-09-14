import { FileSystem  } from "../filesytem/disk";

export const loadData = async () => {
    
    const fileUsers = new FileSystem("users.db");

    fileUsers.readLines(async (line) => {
        
        let user = JSON.parse(line)

        if(!!!user["name"]) user["name"] = user["display_name"]

        if(!!!user["profile"]) user["profile"] = user["picture"]

        if(!!!user["displayName"]) user["displayName"] = user["display_name"]

        const response = await fetch("http://localhost:8080", {
            method: "post",
            body: JSON.stringify(user),
        })

        let data = await response.json()

        if(!response.ok) 
            console.log("user:", user)

        console.log("response:", data.message)
    
        return true;//(!response.ok) 
    })
}
