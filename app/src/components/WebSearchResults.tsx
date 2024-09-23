'use client'

import Link from 'next/link';
import PaginationButtons from './PaginationButtons';
import { ReactNode, useEffect, useState } from 'react';
import { User } from '@/types/types';
import { UserProfile } from './UserProfile';
import { hexToNpub } from '@/utils/utils';
import LastNotes from './search/LastNotes';

type Props = {
    results: User[]
}

export default function WebSearchResults({ results }: Props): ReactNode {
    
    return (
        <div className='w-full mx-auto px-3 sm:pb-24 pb-40'>
            {results.map((user: User) => (
                <div className='lg:flex lg:flex-row m-2 md:m-5 bg-gray-800 rounded-3xl p-2' key={user.pubkey}>
                    <div className='basis-1/1 lg:basis-1/4 p-3 overflow-x-clip'>
                        <Link href='#' className='block'>
                            <UserProfile profile={user.profile} displayName={user.displayName} /> 
                            <div className='group flex flex-col'>
                                <h3 className='text-[16px] lg:text-[22px] text-left mt-3 text-gray-400 font-bold'>
                                    {user.displayName}
                                </h3>
                                <p className='text-[11px] text-gray-300 font-sans'>
                                    {user.about}
                                </p>
                            </div>
                            <div className='p-2 overflow-x-scroll md:overflow-x-clip scroll-m-0'>
                                <p className='text-gray-500 text-[12px] pointer-events-auto select-text'>
                                    {hexToNpub(user.pubkey)}
                                </p>
                            </div>
                            <p className='text-gray-500 text-[12px] font-bold'>Similarity: {user.similarity}</p>
                        </Link>
                    </div>
                    <div className='basis-1/1 lg:w-full p-3'>
                        <LastNotes events={[]} /> 
                    </div>
                </div>
            ))}
            {/* <PaginationButtons /> */}
        </div>
    );
}
