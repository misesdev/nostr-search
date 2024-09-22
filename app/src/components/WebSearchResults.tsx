import Link from 'next/link';
import PaginationButtons from './PaginationButtons';
import { ReactNode } from 'react';
import { User } from '@/types/types';

type Props = {
    results: User[]
}

export default function WebSearchResults({ results }: Props): ReactNode {
    return (
        <div className='w-full mx-auto px-3 sm:pb-24 pb-40 sm:pl-[5%] md:pl-[14%] lg:pl-52'>
            {/* <p className='text-gray-600 text-sm mb-5 mt-3'> */}
            {/*     About {results.searchInformation?.formattedTotalResults} results ( */}
            {/*     {results.searchInformation?.formattedSearchTime} seconds) */}
            {/* </p> */}
            {results.map((result: User) => (
                <div className='mb-8 max-w-xl' key={result.pubkey}>
                    <div className='group flex flex-col'>
                        <Link href={result.profile}>{result.displayName}</Link>
                        <Link
                            href={result.profile}
                            className='group-hover:underline decoration-blue-800 text-xl truncate font-medium text-blue-800'
                        >
                            {result.about}
                        </Link>
                    </div>
                    <p className='text-gray-600'>{result.similarity}</p>
                </div>
            ))}
            <PaginationButtons />
        </div>
    );
}
