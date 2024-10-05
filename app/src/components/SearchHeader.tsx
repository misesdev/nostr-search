'use client'

import Image from 'next/image';
import Link from 'next/link';
import SearchBox from './SearchBox';
import SearchHeaderOptions from './SearchHeaderOptions';
import { ReactNode, useEffect, useState } from 'react';
import { User } from '@/types/types';

export default function SearchHeader(): ReactNode {

    const [user, setUser] = useState<User | null>(null);

    useEffect(() => {
        const localUser = localStorage.getItem("user")

        if(localUser) setUser(JSON.parse(localUser))
    }, [])

    return (
        <header className='top-0 bg-gray-800'>
            <div className='lg:flex w-full p-4 lg:p-6'>
                <div className='hidden lg:flex'>
                    <Link href='/'>
                        <Image
                            src='/logo.png'
                            alt='Nostr Book Users'
                            width={40}
                            height={40}
                            priority
                            style={{ width: 'auto' }}
                        />
                    </Link>
                </div>
                <div className='lg:hidden w-full mb-4 flex px-2'>
                    <Link href='/'>
                        <div className='flex'>
                            {/* <Link href='/'> */}
                                <Image
                                    src='/logo.png'
                                    alt='Nostr Book Users'
                                    width={32}
                                    height={32}
                                    priority
                                    style={{ width: 'auto' }}
                                />
                            {/* </Link> */}
                            <h3 className='text-[16px] font-bold mt-1 ml-5 text-gray-400'>Nosbook</h3>
                        </div>
                    </Link>
                    <div className='flex-1'>
                        { !user &&
                            <Link href='/pubkey' className='bg-[#3e2eb3] float-end text-[12px] text-gray-300 py-2 px-5 rounded-md hover:brightness-105 hover:shadow-md transition-shadow ml-2'>
                                Sign in
                            </Link>
                        }
                        { user && 
                            <Link 
                                href="#" 
                                className='float-end rounded-full w-50 h-50 overflow-hidden border border-[#3e2eb3]'>
                                    <Image 
                                        width={35}
                                        height={35}
                                        className=""
                                        alt={user.displayName}
                                        src={user.profile}
                                    />
                            </Link>
                        }
                    </div>
                </div>
                <div className='flex-1'>
                    <SearchBox />
                </div>
                <div className='hidden lg:flex items-center'>
                    { !user && 
                        <Link 
                            href="/pubkey" 
                            className='bg-[#3e2eb3] text-gray-300 px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow'>
                            Sign in
                        </Link>
                    }
                    { user && 
                        <Link 
                            href="#" 
                            className='float-end rounded-full w-50 h-50 overflow-hidden border border-[#3e2eb3]'>
                                <Image 
                                    width={35}
                                    height={35}
                                    className=""
                                    alt={user.displayName}
                                    src={user.profile}
                                />
                        </Link>
                    }
                </div>
            </div>
            <SearchHeaderOptions />
        </header>
    );
}
