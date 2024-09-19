'use client';

import { RxCross2 } from 'react-icons/rx';
import { BsFillMicFill } from 'react-icons/bs';
import { AiOutlineSearch } from 'react-icons/ai';
import { useState } from 'react';
import { useSearchParams, useRouter } from 'next/navigation';

export default function SearchBox() {
    const searchParams = useSearchParams();
    const router = useRouter();
    const searchTerm = searchParams.get('searchTerm');
    const [term, setTerm] = useState(searchTerm || '');
    const handleSubmit = (e) => {
        e.preventDefault();
        if (!term.trim()) return;
        router.push(`/search/web?searchTerm=${term}`);
    };

    return (
        <form
            onSubmit={handleSubmit}
            className='flex border border-gray-700 rounded-full shadow-lg px-6 py-3 ml-10 mr-5 flex-grow max-w-3xl items-center'
        >
            <input
                type='text'
                placeholder="Search"
                style={{ fontSize: 20, color: "#fff" }}
                    className='flex-grow focus:outline-none font-mono py-1 px-2 bg-transparent'
                value={term}
                onChange={(e) => setTerm(e.target.value)}
            />
            {/* <RxCross2 */}
            {/*     className='text-2xl text-gray-500 cursor-pointer sm:mr-2' */}
            {/*     onClick={() => setTerm('')} */}
            {/* /> */}
            {/* <BsFillMicFill className='hidden sm:inline-flex text-4xl text-blue-500 border-l-2  border-gray-300 mr-3 pl-4' /> */}
            <AiOutlineSearch
                style={{ fontSize: 26 }} className='my-1 text-xl text-gray-50 mr-4'
                onClick={handleSubmit}
            />
        </form>
    );
}
