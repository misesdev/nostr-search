'use client'

import HomeHeader from "@/components/HomeHeader";
import Image from "next/image";
import { useRouter } from "next/navigation";
import {  useState } from "react";
import { AiOutlineUser } from "react-icons/ai"; 

export default function Page() {

    const router = useRouter()
    const [pubkey, setPukey] = useState('')

    const handleSave = () => {
        localStorage.setItem('pubkey', pubkey)
        router.push("/")
    }

    return (
        <>
            <HomeHeader />
            <div className='overflow-auto flex flex-col items-center mt-18'>
                <Image
                    src='/logo.png'
                    alt='Nostr Book Users'
                    width={130}
                    height={100}
                    className="w-[120px] lg:w-[140px]"
                />
                <h2
                    className="text-[20px] lg:text-[24px] text-center mt-10 text-gray-400 font-bold"
                >
                    Nostr Book - Add your pubkey
                </h2>

                <div>
                    <h4
                        className="text-center text-gray-200 mt-10 text-[12px] lg:text-[18px]"
                    >Adding your public key will enhance the search for your profile!</h4>
                </div>

                <div
                    className='flex w-full mt-10 mx-auto max-w-[90%] border border-gray-500 px-5 py-3 rounded-full hover:shadow-md focus-within:shadow-md transition-shadow sm:max-w-xl lg:max-w-2xl'
                >
                    <AiOutlineUser className='text-xl text-gray-500 mr-3' /> 
                    <input
                        type='text'
                        placeholder='Your pubkey: npub...'
                        className='select-none px-1 text-gray-400  bg-transparent flex-grow focus:outline-none'
                        onChange={(e) => setPukey(e.target.value)}
                    />
                </div>

                <div className="mt-20">
                    <button 
                        onClick={handleSave} 
                        className='bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow'>Save Pubkey</button>
                </div>

            </div>
        </>
    );
}
