import { FileSystem  } from "../filesytem/disk";

export const loadData = async () => {
    
    const fileUsers = new FileSystem("./data/users.db")

    // send users
    fileUsers.readLines(async (line) => {
        
        console.log("user:", line)
        
        return true;
    })
}




