import { SearchParams, User } from "@/types/types";
import WebSearchResults from "./WebSearchResults";
import Link from 'next/link';
import Error from "@/app/search/error";
import { generateAvatar } from "@/services/avatar";

const WebSearch = async ({ pubkey, searchTerm }: SearchParams) => {
    
    const response = await fetch(`${process.env.API_ENGINE_URL}/search_users`, { 
        method: "post",
        body: JSON.stringify({
            pubkey,
            searchTerm,
            limit: 48
        })
    })

    if(!response.ok) throw Error('Error')

    const users: User[] = await response.json()

    users.sort((a, b) => b.similarity - a.similarity)

    users.forEach(async (user) => 
    {
        if(!(user.profile.includes("http")))
        {
            user.profile = await generateAvatar(user.pubkey)
        }
    })

    if (!users.length) 
    {
        return (
            <div className='flex flex-col justify-center items-center pt-10'>
                <h1 className='text-[20px] lg:text-3xl mb-4 text-gray-400 text-center'>
                    No users found for `{searchTerm}`
                </h1>
                <p className='text-[12px] lg:text-lg text-gray-300 text-center'>
                    Try searching the web or images for something else{' '}
                    <Link href='/' className='text-blue-500'>
                        Home
                    </Link>
                </p>
            </div>
        )
    }

    return (<div>{users.length && <WebSearchResults results={users} />}</div>)
}

export default WebSearch 
