import { SearchParams, User } from "@/types/types";
import WebSearchResults from "./WebSearchResults";
import Link from 'next/link';
import Error from "@/app/search/error";
import { defaultProfile } from "@/constants";

const SearchResults = async ({ pubkey, searchTerm }: SearchParams) => {
    
    // search
    let response = await fetch('http://localhost:8080/search', {
        method: "post",
        body: JSON.stringify({
            pubkey: pubkey,
            searchTerm: searchTerm
        })
    })

    if(!response.ok) throw Error('Error')

    const results: User[] = await response.json()

    results.sort((a, b) => b.similarity - a.similarity)

    results.forEach(user => {
        if(!user.profile.includes("http") && !user.profile.includes("https"))
        {
            user.profile = defaultProfile
        }
    })

    if (!results.length) {
        return (
            <div className='flex flex-col justify-center items-center pt-10'>
                <h1 className='text-[20px] lg:text-3xl mb-4 text-gray-400 text-center'>
                    No results found for `{searchTerm}`
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

    return (<div>{results.length && <WebSearchResults results={results} />}</div>)
}

export default SearchResults 
