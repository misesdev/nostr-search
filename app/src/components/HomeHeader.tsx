'use client'

import { User } from "@/types/types";
import Link from "next/link";
import { ReactNode, useEffect, useState } from "react";
import Image from "next/image";

type Props = {
    hiddenLogin?: boolean
}

const HomeHeader = ({ hiddenLogin = false }: Props): ReactNode => {

    const [visible, setVisible] = useState(false)
    const [user, setUser] = useState<User | null>(null)

    useEffect(() => {
        const npub = localStorage.getItem("user")

        console.log(npub)

        if(npub) setUser(JSON.parse(npub))

    }, [])

    const deletePubkey = () => {
        localStorage.removeItem('pubkey')
        localStorage.removeItem('user')
        window.location.href = '/'
    }

    if(hiddenLogin) return (
        <header className='flex justify-end p-5 text-sm'></header>
    )

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
                    <div className="relative inline-block text-left">
                        <Link 
                            href="#" 
                            className='float-end rounded-full w-35 h-35 overflow-hidden border border-[#3e2eb3]'
                            onClick={() => setVisible(true)}
                        >
                            <Image 
                                width={35}
                                height={35}
                                className=""
                                alt={user.displayName}
                                src={user.profile}
                            />
                        </Link>
                        { visible &&
                            <div
                                onMouseLeave={() => setVisible(false)}
                                className="absolute right-0 z-10 mt-2 w-56 origin-top-right rounded-md bg-white shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none"
                            >
                                <div className="py-1" role="menu">
                                    <a href="https://find.nosbook.org" 
                                        className="block px-4 py-2 text-sm text-gray-700 hover:text-gray-200 hover:bg-[#3e2eb3]" 
                                        role="menuitem" 
                                        target="_blak"
                                        id="menu-item"
                                        onClick={() => setVisible(false)}
                                    >API</a>
                                    <a href="#" 
                                        onClick={deletePubkey}
                                        className="block px-4 py-2 text-sm text-gray-700 hover:text-gray-200 hover:bg-[#3e2eb3]" 
                                        role="menuitem" 
                                        id="menu-item">Sign Out</a>
                                </div>
                            </div>
                        }
                    </div>
                }
            </div>
        </header>
    )
}

export default HomeHeader
