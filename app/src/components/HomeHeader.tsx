'use client'

import Link from "next/link";
import { ReactNode, useEffect } from "react";

const HomeHeader = (): ReactNode => {

    // var pubkey = null;
    // 
    // useEffect(() => {
    //     const npub = localStorage.getItem("pubkey")

    //     if(npub) pubkey = npub

    // }, [])

    return (
        <header className='flex justify-end p-5 text-sm'>
            <div className="flex space-x-4 items-center">
                <Link 
                    href="/pubkey" 
                    className='bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow'>
                        Sign in
                </Link>
            </div>
        </header>
    )
}

export default HomeHeader
