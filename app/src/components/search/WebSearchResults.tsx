'use client'

import Link from 'next/link';
import PaginationButtons from '../PaginationButtons';
import { ReactNode, useEffect, useState } from 'react';
import { User } from '@/types/types';
import { UserProfile } from '../UserProfile';
import { hexToNpub } from '@/utils/utils';

type Props = {
    results: User[]
}

export default function WebSearchResults({ results }: Props): ReactNode {
    
    return (
        <div className='w-full grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4 md:gap-7 py-5 md:py-8 px-3 md:px-6'>
            {results.map((user: User) => (
                <div className='w-full group' key={user.pubkey}>
                    <div className='p-5 bg-gray-800 rounded-3xl overflow-x-clip'>
                        <div className='overflow-x-clip'>
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
                                <div className='py-2 overflow-x-scroll md:overflow-x-visible scroll-m-0'>
                                    <p className='text-gray-500 text-[12px] pointer-events-auto select-text'>
                                        {hexToNpub(user.pubkey)}
                                    </p>
                                </div>
                                <p className='text-gray-500 text-[12px] font-bold'>Similarity: {user.similarity}</p>
                            </Link>
                        </div>
                    </div>
                </div>
            ))}
            {/* <PaginationButtons /> */}
            <div className='h-12 md:h-24'></div>
        </div>
    );
}
