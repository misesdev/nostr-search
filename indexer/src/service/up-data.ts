import { FileSystem  } from "../filesytem/disk";

export const loadData = async () => {
    
    const fileUsers = new FileSystem("users.db");

    fileUsers.readLines(async (line) => {
        
        let user = JSON.parse(line)
 
        const response = await fetch("http://localhost:8080", {
            method: "post",
            body: JSON.stringify(user),
        })

        let data = await response.json()

        if(!response.ok) 
            console.log("user:", user)

        console.log("response:", data.message)
    
        return true;
    })
}
