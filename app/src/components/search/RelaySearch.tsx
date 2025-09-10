import Link from "next/link"
import { Relay, RelayParams } from "@/types/types"
import { RelaySearchResults } from "./RelaySearchResults"
import { normalizeRelay } from "@/utils/utils"

export const RelaySearch = async ({ searchTerm }: RelayParams) => {
    
    const response = await fetch(`${process.env.API_ENGINE_URL}/relays/search`,{
        method: "post",
        headers: {
            "Accept": "application/json",
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            searchTerm: searchTerm.replace("wss://", ""),
            limit: 100
        })
    })

    if(!response.ok) {
        console.log("response", await response.json())
        throw Error("search request error")
    }

    let results: Relay[] = await response.json()

    results.forEach(relay => relay = normalizeRelay(relay))

    if (!results.length) 
    {
        return (
            <div className='flex flex-col justify-center items-center pt-10'>
                <h1 className='text-[20px] lg:text-3xl mb-4 text-gray-400 text-center'>
                    No relays found for `{searchTerm}`
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

    return <RelaySearchResults relays={results} /> 
}



