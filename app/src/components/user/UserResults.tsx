import { User } from "@/types/types"
import { UserProfile } from "../UserProfile"
import { hexToNpub } from "@/utils/utils"
import toast from "react-hot-toast"
import { Copy } from "lucide-react"

type UserItemProps = {
    user: User
}

export const UserItem = ({ user }: UserItemProps) => {
    
    const handleCopy = () => {
        navigator.clipboard.writeText(hexToNpub(user.pubkey))
        toast.success("Copied npub to clipboard!")
    }

    return (
        <div className="w-full max-w-md rounded-2xl overflow-hidden shadow-md bg-white dark:bg-gray-900 transition hover:shadow-lg">
            {/* Banner */}
            <div className="h-32 w-full bg-cover bg-center">
                <img
                  src={user.banner}
                  alt="Banner"
                  className="h-32 w-full object-cover"
                  onError={(e) => {
                    e.currentTarget.src = "/default-banner.jpg";
                  }}
                />
            </div>

            <div className="p-4 flex flex-col bg-gray-800  sm:flex-row items-center sm:items-start gap-4">
                {/* Foto */}
                <img
                    src={user.picture}
                    alt={user.name}
                    className="w-20 h-20 rounded-full border-4 border-white dark:border-gray-800 -mt-12 sm:mt-0"
                    onError={(e) => e.currentTarget.src = "/default-avatar.png"}
                />

                {/* Info */}
                <div className="flex-1 text-left min-h-[3.8rem]">
                    <h2 className="text-lg font-semibold text-gray-300">{user.display_name || user.name}</h2>
                    <p className="max-w-[18rem] text-sm text-gray-500 dark:text-gray-400 min-h-[3.8rem] line-clamp-2">
                        {user.about}
                    </p>
                    <span className=" text-xs text-gray-400 py-2">
                        <strong>references</strong>: {user.ref_count}
                    </span>
                </div>

                {/* Botão copiar chave */}
                <button
                    onClick={handleCopy}
                    className="p-2 rounded-full bg-gray-100 dark:bg-gray-800 hover:bg-gray-200 dark:hover:bg-gray-700 transition"
                    title="Copiar chave pública"
                >
                    <Copy className="w-5 h-5 text-gray-600 dark:text-gray-300" />
                </button>
            </div>
        </div>
    )
}

type UserListProps = {
    users: User[]
}

export const UsersResults = ({ users }: UserListProps) => {
    return (
        <div className='w-full grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4 md:gap-7 py-5 md:py-8 px-3 md:px-6'>
            { users.map(user => <UserItem key={user.pubkey}user={user} />)}
        </div>
    )
}
