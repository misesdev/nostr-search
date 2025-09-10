'use client'

import { Relay } from "@/types/types"
import { Copy } from "lucide-react"
import Image from "next/image"
import toast from "react-hot-toast"
import { AiOutlineCopy } from "react-icons/ai"

interface Props {
    relay: Relay 
}

export const RelayItem = ({ relay }: Props) => {

    const supported_nips = JSON.parse(relay.supported_nips??"[]") as number[]

    const handleCopy = () => {
        navigator.clipboard.writeText(relay.url)
        toast.success(`Copied ${relay.url} to clipboard!`)
    }

    return (
        <div className="bg-white dark:bg-gray-800 shadow-md rounded-xl p-4 flex flex-col md:flex-row gap-4 transition hover:shadow-lg">
            <div className="flex-shrink-0">
                <img
                    src={relay.icon}
                    alt={relay.name || "Relay Icon"}
                    className="w-16 h-16 rounded-full object-cover"
                />
            </div>

            <div className="flex-1 flex flex-col justify-between">
                <div>
                    <h2 className="text-lg font-semibold text-gray-900 dark:text-gray-100">
                        {relay.name}
                    </h2>
                    {relay.description && (
                        <p className="text-gray-600 dark:text-gray-300 mt-1 text-sm line-clamp-3">
                            {relay.description}
                        </p>
                    )}

                    {relay.software &&
                        <div className="flex-1 items-center mt-1">
                            <span className="text-gray-700 dark:text-gray-300 text-sm">
                                <strong>software</strong>: {relay.software}
                            </span>
                        </div>
                    }
                    
                    {relay.version &&
                        <div className="flex-1 items-center mt-1">
                            <span className="text-gray-700 dark:text-gray-300 text-sm">
                                <strong>version</strong>: {relay.version}
                            </span>
                        </div>
                    }

                    {relay.author && (
                        <div className="flex items-center mt-2">
                            <img
                                src={relay.author.picture}
                                alt={relay.author.display_name}
                                className="w-6 h-6 rounded-full mr-2 object-cover"
                            />
                            <span className="text-gray-700 dark:text-gray-300 text-sm">
                                {relay.author.display_name || relay.author.name}
                                (<strong>Manteiner</strong>)
                            </span>
                        </div>
                    )}
                </div>

                {/* Ações do card */}
                <div className="mt-3 flex items-center justify-between">
                    <span className="text-sm text-gray-500 dark:text-gray-400">
                        {relay.active ? "Active" : "Inactive"} 
                        <span className="text-green-700"> • </span>
                        {relay.ref_count} references
                    </span>
                    <button
                        onClick={handleCopy}
                        className="p-2 rounded-full bg-gray-100 dark:bg-gray-800 hover:bg-gray-200 dark:hover:bg-gray-700 transition"
                    >
                        <Copy className="w-5 h-5 text-gray-600 dark:text-gray-300" />
                    </button>
                </div>
            </div>
        </div>
    )
}
