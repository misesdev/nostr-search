'use client'

import HomeHeader from '@/components/HomeHeader';
import HomeSearch from '@/components/HomeSearch';
import Image from 'next/image';
import { ReactNode } from 'react';

const Home = () : ReactNode => {

    return (
        <>
            <HomeHeader />
            <div className='flex flex-col items-center mt-18'>
                <Image
                    src='/logo.png'
                    alt='Nostr Book - Search Users'
                    width={130}
                    height={100}
                    className='w-130 lg:w-200'
                />
                <h2 
                    style={{ fontSize: 24 }}
                    className="text-[20px] lg:text-[24px] text-gray-400 mt-5 font-bold"
                >
                    Nostr Book - Search Users
                </h2>
                <HomeSearch />
            </div>
        </>
    );
}

export default Home
