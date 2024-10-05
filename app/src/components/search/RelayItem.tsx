'use client'

import { generateAvatar } from "@/services/avatar"
import { RelayInfo } from "@/types/types"
import { useEffect, useState } from "react"
import Image from "next/image"

type Props = {
    relay: string
}

export const RelayItem = ({ relay }: Props) => {

    const [info, setInfo] = useState<RelayInfo | null>({ address: relay })

    useEffect(() => {
        try {
            fetch(relay.replace("wss://", "https://"), {
                headers: { "Accept": "application/nostr+json" }
            }).then(resp => resp.json()).then(async (data) => {
                try {
                    data["address"] = relay
                    if(!data.icon) data.icon = await generateAvatar(relay)
                    new URL(data.icon)
                } catch {
                    data.icon = await generateAvatar(relay)
                }
                setInfo(data)
            }).catch(() => setInfo(null))
        } 
        catch { setInfo(null) }
    }, [])

    const handleIconError = () => setInfo(null)

    if(!info)
        return <></>

    return (
        <div className='w-full group'>
            <div className='p-5 bg-gray-800 rounded-3xl overflow-x-clip'>
                <div className="overflow-hidden w-[80px] h-[80px] items-center border-4 border-[#3e2eb3] rounded-3xl">
                    <Image
                        width={80}
                        height={80}
                        src={info.icon ?? ""}
                        alt={info.description ?? ""}
                        className="min-h-[80px] min-w-[80px]"
                        onError={handleIconError}
                    />
                </div>
                <p className="text-gray-200 font-bold p-5">
                    {info.address}
                </p>
            </div>
        </div>
    )
}
