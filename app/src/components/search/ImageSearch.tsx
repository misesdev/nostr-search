import ImageSearchResults from '@/components/search/ImageSearchResults';
import { SearchParams, User } from '@/types/types';
import Link from 'next/link';

const ImageSearch = async ({ searchTerm }: SearchParams) => {

    const response = await fetch(`${process.env.API_ENGINE_URL}/user/search`, {
        method: "post",
        headers: {
            "Accept": "application/json",
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            searchTerm,
            limit: 100
        })
    })

    if(!response.ok) throw Error('Error')

    const users: User[] = await response.json()

    const results = users.filter(user => user.picture?.includes("http"))

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

    return (<div>{results.length && <ImageSearchResults results={results} />}</div>)
}

export default ImageSearch
