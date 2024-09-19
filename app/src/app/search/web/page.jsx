import WebSearchResults from '@/components/WebSearchResults';
import Link from 'next/link';

export default async function Page({ searchParams }) {
    // const startIndex = searchParams.start || '1';
    await new Promise((resolve) => setTimeout(resolve, 1000));
    
    try {
        // const response = await fetch(
        //     `https://www.googleapis.com/customsearch/v1?key=${process.env.API_KEY}&cx=${process.env.CONTEXT_KEY}&q=${searchParams.searchTerm}'}&start=${startIndex}`
        // );
        // if (!response.ok) throw new Error('Something went wrong');
        const data = {} //await response.json();
        const results = data?.items;

        if (!results) {
            return (
                <div className='flex flex-col justify-center items-center pt-10'>
                    <h1 className='text-3xl mb-4 text-gray-400'>
                        No results found for <strong className="text-gray-600">{searchParams.searchTerm}</strong>
                    </h1>
                    <p className='text-lg text-gray-300'>
                        Try searching the web or images for something else {' '}
                        <Link href='/' className='text-[#3e2eb3]'>
                            Home
                        </Link>
                    </p>
                </div>
            );
        }

        return <div>{results && <WebSearchResults results={data} />}</div>;

    } catch(error) {
        console.log(error)
        return (
            <div className="flex flex-col justify-center items-center pt-10">
                <h1 className="text-3xl mb-4 text-gray-400">Something went wrong</h1>
                <Link href="/" className="text-[#3e2eb3]">Go back home</Link>
            </div>
        )
    }
}
