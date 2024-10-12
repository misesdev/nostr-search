'use client'

import { generateAvatar } from "@/services/avatar"
import { RelayInfo } from "@/types/types"
import { useEffect, useState } from "react"
import Image from "next/image"
import toast from "react-hot-toast"
import { RelayLoading } from "../relay/RelayLoading"
import { AiOutlineCopy } from "react-icons/ai"
import { defaultProfile } from "@/constants"

type Props = {
    relay: string
}

export const RelayItem = ({ relay }: Props) => {

    const [loading, setLoading] = useState(true)
    const [info, setInfo] = useState<RelayInfo | null>({ address: relay })

    useEffect(() => { 
        fetch(relay.replace("wss", "https"), {
            headers: { "Accept": "application/nostr+json" },
        }).then(resp => resp.json())
        .then(async (data) => {
            data["address"] = relay
            try { new URL(data.icon) } 
            catch { 
                data.icon = await generateAvatar(relay)  
            }
            setLoading(false)
            setInfo(data)
        }).catch(() => {
            setLoading(false)
            setInfo(null)
        }) 
    }, [relay])

    const copyRelay = () => {
        navigator.clipboard.writeText(info?.address ?? "");
        toast.success(`Copied ${relay} to clipboard!`)
    }

    if(loading)
        return <RelayLoading />

    if(!info)
         return <></>

    return (
        <div className='w-full group'>
            <div className='min-h-[320px] p-5 bg-gray-800 rounded-3xl overflow-x-clip'>
                <div className="w-full flex">
                    <div className="flex items-center overflow-hidden w-[80px] h-[80px] border-4 border-[#3e2eb3] rounded-[12px]">
                        <Image
                            width={80}
                            height={80}
                            src={info.icon ?? defaultProfile}
                            alt={info?.description ?? ""}
                            className="min-h-[80px] min-w-[80px]"
                            style={{ backgroundPosition: "50%" }}
                            //onError={() => setError(true)}
                        />
                    </div>
                    <div className="items-end">
                        <button onClick={() => copyRelay()} 
                            className="flex text-gray-200 font-bold py-4 px-6 mx-5 bg-[#3e2eb3] rounded-[20px] cursor-pointer">
                            {info?.address} 
                            <AiOutlineCopy className="text-gray-200 m-1 mx-2 text-[18px]" />
                        </button>
                    </div>
                </div>
                <div className="w-full pt-1">
                    <label className="text-gray-200 font-bold text-[12px]">
                        {info?.description ?? ""}
                    </label>
                </div>

                <div className="w-full pt-1">
                    <label className="text-gray-200 font text-[12px] mb-1">
                        Supported Nips:
                    </label>
                    <div className="w-full overflow-x-auto h-10" style={{ scrollbarWidth: 'thin' }}>
                        {info?.supported_nips?.map((nip, key) => {
                            return (
                                <span key={key} className="font-bold text-[12px] text-gray-300 p-1 mx-1 bg-[#3e2eb3] rounded-[4px]">{nip}</span>
                            )
                        })}
                    </div>
                </div>

                { info?.software && 
                    <div className="w-full pt-1 overflow-clip">
                        <label className="text-gray-200 font text-[12px] mb-1">
                            Software: {info?.software}
                        </label>
                    </div>
                }
                { info?.version && 
                    <div className="w-full pt-1">
                        <label className="text-gray-200 font text-[12px] mb-1">
                            Version: {info.version}
                        </label>
                    </div>
                }
                { info?.contact && 
                    <div className="w-full pt-1 overflow-clip">
                        <label className="text-gray-200 font text-[12px] mb-1">
                            Contact: {info.contact}
                        </label>
                    </div>
                }
            </div>
        </div>
    )
}
