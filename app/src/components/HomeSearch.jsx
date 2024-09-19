'use client';

import { useState } from 'react';
import { AiOutlineSearch } from 'react-icons/ai';
import { BsFillMicFill } from 'react-icons/bs';
import { useRouter } from 'next/navigation';

export default function HomeSearch() {
    
    const [input, setInput] = useState('');
    
    const [randomSearchLoading, setRandomSearchLoading] = useState(false);
    
    const router = useRouter();
    
    const handleSubmit = (e) => {
        e.preventDefault();
        if (!input.trim()) return;
        router.push(`/search/web?searchTerm=${input}`);
    };

    const handleDonate = () => router.push('/donate')

    const randomSearch = async () => {
        setRandomSearchLoading(true);
        const response = await fetch('https://random-word-api.herokuapp.com/word')
            .then((res) => res.json())
            .then((data) => data[0]);
        if (!response) return;
        router.push(`/search/web?searchTerm=${response}`);
        setRandomSearchLoading(false);
    };

    return (
        <>
            <form
                onSubmit={handleSubmit}
                className='bg-gray-800 flex w-full mt-5 mx-auto max-w-[90%] border border-gray-700 px-5 py-3 rounded-full hover:shadow-md focus-within:shadow-md transition-shadow sm:max-w-xl lg:max-w-2xl'
            >
                <AiOutlineSearch style={{ fontSize: 26 }} className='my-1 text-xl text-gray-50 mr-4' />
                <input
                    type='text'
                    placeholder="Search"
                    style={{ fontSize: 20, color: "#fff" }}
                    className='flex-grow focus:outline-none font-mono py-1 px-2 bg-transparent'
                    onChange={(e) => setInput(e.target.value)}
                />
                {/* <BsFillMicFill className='text-lg' /> */}
            </form>
            <div className='flex flex-col space-y-2 sm:space-y-0 justify-center sm:flex-row mt-8 sm:space-x-4'>
                <button
                    className='bg-[#f8f9fa] rounded-md text-sm text-gray-800 hover:ring-gray-200 focus:outline-none active:ring-gray-300 hover:shadow-md w-36 h-10 transition-shadow'
                    onClick={handleDonate}
                >
                    Donate
                </button>
                <button
                    disabled={randomSearchLoading}
                    className='bg-[#f8f9fa] rounded-md text-sm text-gray-800 hover:ring-gray-200 focus:outline-none active:ring-gray-300 hover:shadow-md w-36 h-10 transition-shadow disabled:opacity-80 disabled:shadow-sm'
                    onClick={randomSearch}
                >
                    {randomSearchLoading ? 'Loading...' : 'I am feeling lucky'}
                </button>
            </div>
        </>
    );
}
