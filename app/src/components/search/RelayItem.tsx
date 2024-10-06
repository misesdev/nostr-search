'use client'

import { generateAvatar } from "@/services/avatar"
import { RelayInfo } from "@/types/types"
import { useEffect, useState } from "react"
import Image from "next/image"
import toast from "react-hot-toast"

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
                    if(new URL(data.icon)) data.icon = await generateAvatar(relay)
                } catch {
                    data.icon = await generateAvatar(relay)
                }
                setInfo(data)
                console.log(data)
            }).catch(() => setInfo(null))
        } 
        catch { setInfo(null) }
    }, [relay])

    const handleIconError = () => setInfo(null)

    const copyRelay = () => {
        navigator.clipboard.writeText(info?.address ?? "");
        toast.success("Copied relay to clipboard!")
    }

    if(!info)
        return <></>

    return (
        <div className='w-full group cursor-pointer' onClick={() => copyRelay()}>
            <div className='p-5 bg-gray-800 rounded-3xl overflow-x-clip'>
                <div className="w-full flex">
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
                    <div className="">
                        {/* <button  */}
                        {/*     className="text-gray-200 bg-[#3e2eb3] px-4 py-1 rounded-[4px] float-end" */}
                        {/*     onClick={() => copyRelay(info.address ?? "")} */}
                        {/* >copy</button> */}
                        <h3 className="text-gray-200 font-bold p-5">
                            {info.address}
                        </h3>
                    </div>
                </div>
                <div className="w-full pt-1">
                    <label className="text-gray-200 font-bold text-[12px]">
                        {info.description ?? ""}
                    </label>
                </div>

                <div className="w-full pt-1">
                    <label className="text-gray-200 font text-[12px] mb-1">
                        Supported Nips:
                    </label>
                    <div className="w-full overflow-x-scroll h-10">
                        {info.supported_nips?.map((nip, key) => {
                            return (
                                <span key={key} className="font-bold text-[12px] text-gray-300 p-1 mx-1 bg-[#3e2eb3] rounded-[4px]">{nip}</span>
                            )
                        })}
                    </div>
                </div>

                { info.software && 
                    <div className="w-full pt-1 overflow-clip">
                        <label className="text-gray-200 font text-[12px] mb-1">
                            Software: {info.software}
                        </label>
                    </div>
                }
                { info.version && 
                    <div className="w-full pt-1">
                        <label className="text-gray-200 font text-[12px] mb-1">
                            Version: {info.version}
                        </label>
                    </div>
                }
                { info.contact && 
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
