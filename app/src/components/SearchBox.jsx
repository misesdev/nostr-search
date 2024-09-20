'use client';

import { AiOutlineSearch } from 'react-icons/ai';
import { useEffect, useState } from 'react';
import { useSearchParams } from 'next/navigation';

const defaultPubkey = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27"

export default function SearchBox() {
    const searchParams = useSearchParams();
    const searchTerm = searchParams.get('searchTerm');
    const [pubkey, setPubkey] = useState(defaultPubkey);
    const [term, setTerm] = useState(searchTerm || '');
    
    useEffect(() => {
        const pubkey = searchParams.get('pubkey')

        if(pubkey) setPubkey(pubkey) 
    }, [searchParams])

    const handleSubmit = (form) => {
        form.preventDefault();
        if (!term.trim()) return;
        form.target.submit()
    };

    return (
        <form method='get' action='/search/web'
            onSubmit={handleSubmit}
            className='flex border border-gray-500 rounded-full shadow-lg px-6 py-3 lg:ml-10 lg:mr-5 flex-grow lg:max-w-3xl items-center'
        >
            <AiOutlineSearch
                className='text-2xl sm:inline-flex text-blue-500 cursor-pointer'
                onClick={handleSubmit}
            />
            <input
                type='text'
                placeholder="Search"
                className='bg-transparent mx-4 text-gray-100 w-full focus:outline-none'
                value={term}
                name="searchTerm"
                onChange={(e) => setTerm(e.target.value)}
            />
            <input type='hidden' name='pubkey' value={pubkey} />
            {/* <RxCross2 */}
            {/*     className='text-2xl text-gray-500 cursor-pointer sm:mr-2' */}
            {/*     onClick={() => setTerm('')} */}
            {/* /> */}
            {/* <BsFillMicFill className='hidden sm:inline-flex text-4xl text-blue-500 border-l-2  border-gray-300 mr-3 pl-4' /> */}
        </form>
    );
}


