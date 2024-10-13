'use client'

import { User } from "@/types/types"
import Link from "next/link"
import { useState } from "react"
import Image from "next/image"

type Props = {
    user: User
}

export const ImageItem = ({ user }: Props) => {

    const [error, setError] = useState(false)

    if(error) return <></>

    return (
        <div className='mb-8'>
            <div className='group'>
                <Link href={user.profile} target='_blank'>
                    <Image
                        width={500}
                        height={500}
                        src={user.profile}
                        alt={user.name}
                        onError={() => setError(true)}
                        className='h-60 group-hover:shadow-xl w-full object-contain transition-shadow duration-300'
                    />
                </Link>
                <Link href={user.profile}>
                    <h2 className='group-hover:underline truncate text-xl'>
                        {user.about}
                    </h2>
                </Link>
                <Link href={user.profile}>
                    <p className='group-hover:underline truncate text-gray-600'>
                        {user.displayName}
                    </p>
                </Link>
            </div>
        </div> 
    )
}
