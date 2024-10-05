'use client';

import { AiOutlineSearch } from 'react-icons/ai';
import { ReactNode, useEffect, useState } from 'react';
import { useSearchParams } from 'next/navigation';
import { defaultPubkey } from '@/constants';

export default function SearchBox() : ReactNode {
    const searchParams = useSearchParams();
    const searchTerm = searchParams.get('searchTerm');
    const [pubkey, setPubkey] = useState(defaultPubkey);
    const [term, setTerm] = useState(searchTerm || '');
    
    useEffect(() => {
        const pubkey = searchParams.get('pubkey')

        if(pubkey) setPubkey(pubkey) 
    }, [searchParams])

    const handleSubmit = (form: any) => {
        form.preventDefault();
        if (!term.trim()) return;
        form.target.submit()
    }

    return (
        <form method='get' action='/search/web'
            onSubmit={handleSubmit}
            className='flex border border-gray-500 rounded-full shadow-lg px-6 py-3 lg:ml-10 lg:mr-5 flex-grow lg:max-w-3xl items-center'
        >  
            <AiOutlineSearch
                className='text-2xl sm:inline-flex text-gray-500 cursor-pointer' onClick={handleSubmit} 
            />
            <input
                type='text'
                placeholder="Search"
                autoComplete='off'
                className='bg-transparent mx-4 text-gray-300 w-full focus:outline-none'
                value={term}
                name="searchTerm"
                minLength={3}
                onChange={(e) => setTerm(e.target.value)}
            />
            <input type='hidden' name='pubkey' value={pubkey} />
        </form>
    );
}


