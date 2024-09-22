'use client';

import { ReactNode, useEffect, useState } from 'react';
import { AiOutlineSearch } from 'react-icons/ai';
import { useRouter } from 'next/navigation';
import { defaultPubkey } from '@/constants/pubkey';

export default function HomeSearch() : ReactNode {
    
    const router = useRouter()
    const [input, setInput] = useState('')
    const [userPubkey, setUserPubkey] = useState(false)
    const [pubkey, setPubkey] = useState(defaultPubkey)

    useEffect(() => {
        const npub = localStorage.getItem('pubkey')

        if(npub) {
            setUserPubkey(true)
            setPubkey(npub)
        }
    }, [])

    const deletePubkey = () => {
        localStorage.removeItem('pubkey')
        setUserPubkey(false)
    }
    
    const handleSubmit = (form: any) => {
        form.preventDefault();
        if (!input.trim()) return;
        form.target.submit()
    };
            
    return (
        <>
            <form method='get'
                action="/search/web"
                onSubmit={handleSubmit}
                className='flex w-full mt-10 mx-auto max-w-[90%] border border-gray-500 px-5 py-3 rounded-full hover:shadow-md focus-within:shadow-md transition-shadow sm:max-w-xl lg:max-w-2xl'
            >
                <AiOutlineSearch className='text-[26px] text-gray-500 mr-3' />
                <input
                    type='text'
                    name="searchTerm"
                    placeholder="Search"
                    autoComplete='off'
                    className='text-[16px] text-gray-200 bg-transparent flex-grow focus:outline-none'
                    onChange={(e) => setInput(e.target.value)}
                />
                <input type="hidden" name="pubkey" value={userPubkey ? pubkey : defaultPubkey} />
               {/*  <BsFillMicFill className='text-lg' /> */}
            </form>
            <div className='flex flex-col space-y-2 sm:space-y-0 justify-center sm:flex-row mt-8 sm:space-x-4'>
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
                <button
                    className='bg-[#3e2eb3] rounded-md text-sm text-gray-200 font-bold hover:ring-gray-200 focus:outline-none active:ring-gray-300 hover:shadow-md w-36 h-10 transition-shadow'
                    onClick={() => router.push('/donate')}
                >
                    Donate
                </button>
            </div>
        </>
    );
}
