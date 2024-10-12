'use client'

import { defaultProfile } from "@/constants"
import { generateAvatar } from "@/services/avatar"
import Image from "next/image"
import { useEffect, useState } from "react"

type Props = {
    profile: string,
    displayName: string
}

export const UserProfile = ({ profile, displayName }: Props) => {
    
    const [loading, setLoading] = useState(true)
    const [content, setContent] = useState<string>(!profile.includes("http") ? defaultProfile : profile)

    useEffect(() => {
        const load = async () => {
            if(!profile.includes("http")) {
                const picture = await generateAvatar(profile ?? displayName)
                setContent(picture)
            }                
            setLoading(false)
        }

        load()
    }, [profile])

    const handleGeneric = async () => {        
        const avatar = await generateAvatar(displayName)
        setContent(avatar)
    }

    if(loading)
        return <></>

    return (
        <div className="flex items-center overflow-hidden w-[100px] h-[100px] border-4 border-[#3e2eb3] rounded-[20px]">
            <Image
                width={100}
                height={100}
                src={content}
                alt={displayName}
                className="min-h-[100px] min-w-[100px]"
                style={{ backgroundPosition: "50%" }}
                onError={handleGeneric}
            />
        </div>
    )
}


