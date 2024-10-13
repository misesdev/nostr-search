'use client'

import { defaultProfile } from "@/constants"
import { generateAvatar } from "@/services/avatar"
import Image from "next/image"
import { useEffect, useState } from "react"

type Props = {
    size?: number,
    profile: string,
    displayName: string
}

export const UserProfile = ({ profile, displayName, size = 100 }: Props) => {
    
    const [loading, setLoading] = useState(true)
    const [content, setContent] = useState<string>(profile)

    useEffect(() => {
        const load = async () => {
            try { new URL(profile) } 
            catch {
                const picture = await generateAvatar(profile ?? displayName)
                setContent(picture)
            }
            setLoading(false)
        }

        load()
    }, [profile, displayName])

    const handleGeneric = async () => {        
        const avatar = await generateAvatar(displayName)
        setContent(avatar)
    }

    if(loading)
        return <></>

    return (
        <div className={`flex items-center overflow-hidden w-[${size}px] h-[${size}px] border-4 border-[#3e2eb3] rounded-[20px]`}>
            <Image
                width={size}
                height={size}
                src={content}
                alt={displayName}
                className={`min-h-[${size}px] min-w-[${size}px]`}
                style={{ backgroundPosition: "50%" }}
                onError={handleGeneric}
            />
        </div>
    )
}


