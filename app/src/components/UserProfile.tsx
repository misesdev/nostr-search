'use client'

import { generateAvatar } from "@/services/avatar"
import Image from "next/image"
import { useState } from "react"

type Props = {
    profile: string,
    displayName: string
}

export const UserProfile = ({ profile, displayName }: Props) => {
    
    const [content, setContent] = useState(profile)

    const handleGeneric = async () => {        
        const avatar = await generateAvatar(displayName)

        setContent(avatar)
    }

    return (
        <div className="overflow-hidden w-[130px] h-[130px] p-0 flex items-center border-4 border-[#3e2eb3] rounded-3xl">
            <div className="">
                <Image
                    width={130}
                    height={130}
                    src={content}
                    alt={displayName}
                    className="m-0 p-0 min-h-[130px] min-w-[130px] w-auto"
                    onError={handleGeneric}
                />
            </div>
        </div>
    )
}


