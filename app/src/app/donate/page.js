'use client'

import HomeHeader from "@/components/HomeHeader";
import Image from "next/image";
import { useRouter } from "next/navigation";

export default function Page()
{
    const router = useRouter()

    return (
        <>
            <HomeHeader />
            <div className='flex flex-col items-center mt-18'>
                <Image
                    src='/logo.png'
                    alt='Nostr Book Users'
                    width={140}
                    height={100}
                />
                <h2
                    className="text-[20px] lb:text-[24px] text-center mt-10 text-gray-400 font-bold"
                >
                    Nostr Book - Donate to this Project
                </h2>

                <div className="mt-10 p-10 flex border border-gray-500 rounded-sm px-6 py-3 flex-grow items-center" >
                    <h3 
                        className="text-blue-400 "
                    >greatasphalt42@walletofsatoshi.com</h3>
                </div>

                <div className="mt-20">
                    <button 
                        onClick={() => router.push('/')} 
                        className='bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow'>
                        Go Back
                    </button>
                </div>

            </div>
        </>
    );
}
