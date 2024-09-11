import { FileSystem  } from "../filesytem/disk";

export const loadData = () => {
    
    const fileUsers = new FileSystem("users.db");

    fileUsers.readLines(line => {
        let user = JSON.parse(line)

        console.log(user)
        //fetch("localhost:9090/loadUser", user)
    })
}
