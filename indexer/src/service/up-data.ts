import { FileSystem  } from "../filesytem/disk";
import axios from "axios"

const client = axios.create({ 
    baseURL: "http://localhost:8080",
    responseType: "json",
    headers: {
        "Content-Type": "application/json"
    },
})

//const defaultProfie = "https://blob.nostroogle.org/files/storage/ec362271f59dbc624ae0c9654/7R0UeSxaHgeNrLJ61WBBy9Mx3blWOnHaJEov5A37.webp"
const defaultProfie = "https://blob.nostroogle.org/files/storage/ec362271f59dbc624ae0c9654/njuHESHnTKmNvFPQdeZOX0FeB4LZ0tfGFQqFoe7k.jpg"

export const loadData = async () => {
    
    const fileUsers = new FileSystem("users.db");

    fileUsers.readLines(async (line) => {
        
        let user = JSON.parse(line)

        if(!!!user["displayName"]) user["displayName"] = user["name"];

        if(!!!user["profile"]) user["profile"] = defaultProfie;
                        
        const response = await client.post("/", JSON.stringify(user))

        if(response.status == 200)
            console.log(`${response.data.data}`);
        else 
            console.log(response.data.data);

    })
}
