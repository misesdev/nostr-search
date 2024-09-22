import Link from 'next/link';
import PaginationButtons from './PaginationButtons';
import Image from 'next/image';
import { ReactNode } from 'react';
import { User } from '@/types/types';

type Props = {
    results: User[]
}

export default function ImageSearchResults({ results }: Props): ReactNode {
    return (
        <div className='sm:pb-24 pb-40 mt-4'>
            <div className='grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 px-3 space-x-4'>
                {results.map((result: User) => (
                    <div className='mb-8' key={result.profile}>
                        <div className='group'>
                            <Link href={result.profile}>
                                <Image
                                    src={result.profile}
                                    alt={result.name}
                                    className='h-60 group-hover:shadow-xl w-full object-contain transition-shadow duration-300'
                                />
                            </Link>
                            <Link href={result.profile}>
                                <h2 className='group-hover:underline truncate text-xl'>
                                    {result.about}
                                </h2>
                            </Link>
                            <Link href={result.profile}>
                                <p className='group-hover:underline truncate text-gray-600'>
                                    {result.displayName}
                                </p>
                            </Link>
                        </div>
                    </div>
                ))}
            </div>
            <div className='ml-16'>
                <PaginationButtons />
            </div>
        </div>
    );
}
