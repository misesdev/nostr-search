'use client'

import { User } from "@/types/types";
import Link from "next/link";
import { ReactNode, useEffect, useState } from "react";
import Image from "next/image";

const HomeHeader = (): ReactNode => {

    const [user, setUser] = useState<User | null>(null);

    useEffect(() => {
        const npub = localStorage.getItem("user")

        console.log(npub)

        if(npub) setUser(JSON.parse(npub))

    }, [])

    return (
        <header className='flex justify-end p-5 text-sm'>
            <div className="flex space-x-4 items-center">
                { !user &&
                    <Link 
                        href="/pubkey" 
                        className='bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow'>
                            Sign in
                    </Link>
                }
                { user && 
                    <Link 
                        href="#" 
                        className='float-end rounded-full w-35 h-35 overflow-hidden border border-[#3e2eb3]'>
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
        </header>
    )
}

export default HomeHeader
