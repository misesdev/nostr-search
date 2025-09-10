'use client'

import { User } from "@/types/types"
import toast from "react-hot-toast"
import { Copy, LinkIcon } from "lucide-react"

type Props = {
    user: User
}

export const ImageItem = ({ user }: Props) => {

    if(!user.picture) return <></>

    const handleCopy = () => {
        navigator.clipboard.writeText(user.picture)
        toast.success("Copied npub to clipboard!")
    }

    return (
        <div className="bg-white dark:bg-gray-800 shadow-md rounded-xl overflow-hidden flex flex-col transition hover:shadow-lg">
            {/* Imagem */}
            <div className="w-full h-64 md:h-48 lg:h-64 overflow-hidden">
                <img
                    src={user.picture}
                    alt={`Post ${user.name}`}
                    className="w-full h-full object-cover"
                />
            </div>

            {/* Conteúdo abaixo da imagem */}
            <div className="p-4 flex flex-col gap-2">
                {/* Autor */}
                <div className="flex items-center gap-2">
                    <img
                        src={user.picture}
                        alt={user.display_name || user.name}
                        className="w-8 h-8 rounded-full object-cover"
                    />
                    <span className="text-gray-900 dark:text-gray-100 font-medium text-sm">
                        {user.display_name || user.name}
                    </span>
                </div>

                {/* Ações */}
                <div className="mt-2 flex justify-between items-center">
                    <span className="text-gray-500 dark:text-gray-400 text-xs">
                        Post by: {user.name}
                    </span>
                    <div className="flex gap-2">
                        <button
                            onClick={handleCopy}
                            className="p-2 rounded-full bg-gray-100 dark:bg-gray-800 hover:bg-gray-200 dark:hover:bg-gray-700 transition"
                        >
                            <Copy className="w-5 h-5 text-gray-600 dark:text-gray-300" />
                        </button>
                        <a
                            href={user.picture}
                            target="_blank"
                            rel="noopener noreferrer"
                            className="p-2 rounded-full bg-gray-100 dark:bg-gray-800 hover:bg-gray-200 dark:hover:bg-gray-700 transition"
                        >
                            <LinkIcon className="w-5 h-5 text-gray-600 dark:text-gray-300" />
                        </a>
                    </div>
                </div>
            </div>
        </div>
    )
}
