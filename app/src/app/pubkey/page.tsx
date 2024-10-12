'use client'

import HomeHeader from "@/components/HomeHeader";
import Image from "next/image";
import { useRouter } from "next/navigation";
import {  useState } from "react";
import { AiOutlineUser } from "react-icons/ai"; 
import { validatePubkey } from "@/utils/utils";
import { UserProfile } from "@/components/UserProfile";
import { User } from "@/types/types";

export default function Page() {

    const router = useRouter()
    const [pubkey, setPukey] = useState('')
    const [isValid, setValid] = useState(false)
    const [loading, setLoading] = useState(false)
    const [profile, setProfile] = useState('')
    const [displayName, setDisplayName] = useState('')

    const [user, setUser] = useState<User | null>(null)

    const validateField = async (npub: string) => {
        
        let pubkey = validatePubkey(npub);

        if(pubkey)
        {
            let response = await fetch('/data/user', {
                method: "post",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify({
                    pubkey: pubkey
                })
            })

            if(response.ok) 
            {
                let data = await response.json()

                if(!data?.message) {
                    setDisplayName(data.displayName)
                    setProfile(data.profile)
                    setUser(data)
                }

                if(data?.message) {
                    setDisplayName('')
                    setProfile('')
                    setUser(null)
                }
            }

            setPukey(pubkey)
            setValid(true)
            return;
        }

        setValid(false)
        setProfile('')
        setDisplayName('')
    }

    const handleSave = async () => {

        if(!isValid) return

        setLoading(true)
         
        localStorage.setItem('pubkey', pubkey)
        localStorage.setItem('user', JSON.stringify(user))

        setTimeout(() => router.push('/'), 500)
       
        setLoading(false)
    }

    return (
        <>
            <HomeHeader hiddenLogin />
            <div className='overflow-auto flex flex-col items-center mt-18'>
                <div className="overflow-auto flex flex-col items-center mt-18" >

                    { isValid && profile && <UserProfile size={150} profile={profile} displayName={displayName} /> }
                    { isValid && profile &&
                        <h2 className="text-[20px] lg:text-[24px] text-center mt-10 text-gray-400 font-bold">
                            {displayName}    
                        </h2>
                    }
                    { !isValid && !profile &&
                        <div className="overflow-auto flex flex-col items-center mt-18" >
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
                        </div>
                    }
                </div>

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
                        onChange={(e) => validateField(e.target.value)}
                        onKeyDown={(event) => { if(event.key == "Enter") handleSave() }}
                    />
                </div>

                <div className="mt-20">
                    <button 
                        onClick={handleSave}
                        disabled={!isValid}
                        className={`${ isValid ? 'bg-[#3e2eb3] text-white' : 'bg-[#221866] text-gray-400' } px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow`}
                    >
                        { loading ? 'Loading' : 'Save Pubkey' }
                    </button>
                </div>

            </div>
        </>
    );
}
