import { FileSystem  } from "../filesytem/disk";
import { sendFriends } from "./sends/friends";
import { sendUsers } from "./sends/users";

type Props = {
    users: boolean,
    friends: boolean
}

export const loadData = async ({ users = true, friends = true }: Props) => {
    
    const fileUsers = new FileSystem("./data/users.db")
    const fileFriends = new FileSystem("./data/friends.db")

    // send users
    if(users) await sendUsers(fileUsers)    

    // send friends
    if(friends) await sendFriends(fileFriends)
    
}




