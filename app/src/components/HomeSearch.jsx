'use client';

import { useEffect, useState } from 'react';
import { AiOutlineSearch } from 'react-icons/ai';
import { useRouter } from 'next/navigation';

const defaultPubkey = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27"

export default function HomeSearch() {
    
    const router = useRouter();   
    const [input, setInput] = useState('')
    const [userPubkey, setUserPubkey] = useState(false)

    useEffect(() => {
        const pubkey = localStorage.getItem('pubkey')

        if(pubkey) setUserPubkey(true)
        
        if(!pubkey) localStorage.setItem('pubkey', defaultPubkey)

    }, [])

    const deletePubkey = () => {
        localStorage.removeItem('pubkey')
        setUserPubkey(false)
    }
    
    const handleSubmit = (e) => {
        e.preventDefault();
        if (!input.trim()) return;
        router.push(`/search/web?searchTerm=${input}`);
    };
            
    return (
        <>
            <form
                onSubmit={handleSubmit}
                className='flex w-full mt-5 mx-auto max-w-[90%] border border-gray-500 px-5 py-3 rounded-full hover:shadow-md focus-within:shadow-md transition-shadow sm:max-w-xl lg:max-w-2xl'
            >
                <AiOutlineSearch className='text-[26px] text-gray-500 mr-3' />
                <input
                    type='text'
                    placeholder="Search"
                    className='text-[16px] text-gray-200 bg-transparent flex-grow focus:outline-none'
                    onChange={(e) => setInput(e.target.value)}
                />
               {/*  <BsFillMicFill className='text-lg' /> */}
            </form>
            <div className='flex flex-col space-y-2 sm:space-y-0 justify-center sm:flex-row mt-8 sm:space-x-4'>
                <button
                    className='bg-[#3e2eb3] rounded-md text-sm text-gray-200 font-bold hover:ring-gray-200 focus:outline-none active:ring-gray-300 hover:shadow-md w-36 h-10 transition-shadow'
                    onClick={() => router.push('/donate')}
                >
                    Donate
                </button>
                { !userPubkey && 
                    <button
                        className='bg-[#f8f9fa] rounded-md text-sm text-gray-800 font-bold hover:ring-gray-200 focus:outline-none active:ring-gray-300 hover:shadow-md w-36 h-10 transition-shadow disabled:opacity-80 disabled:shadow-sm'
                        onClick={() => router.push('/pubkey')}
                    >
                        Add Pubkey                                    
                    </button>
                }
                { userPubkey && 
                    <button
                        className='bg-gray-500 rounded-md text-sm text-gray-200 font-bold hover:ring-gray-200 focus:outline-none active:ring-gray-300 hover:shadow-md w-36 h-10 transition-shadow disabled:opacity-80 disabled:shadow-sm'
                        onClick={deletePubkey}
                    >
                        Delete Pubkey                                    
                    </button>
                }            
            </div>
        </>
    );
}
