import { User } from "@/types/types"
import { UserProfile } from "../UserProfile"
import { hexToBytes, hexToNpub } from "@/utils/utils"
import { bech32 } from "bech32"
import toast from "react-hot-toast"
import { AiOutlineCopy } from "react-icons/ai"

const copyToClipboard = (pubkey: string) => {
    const words = bech32.toWords(hexToBytes(pubkey))
    const npub = bech32.encode("npub", words)
    navigator.clipboard.writeText(npub)
    toast.success("Copied npub to clipboard!")
}

type UserItemProps = {
    user: User
}

export const UserItem = ({ user }: UserItemProps) => {

    return (
        <div className='w-full group' key={user.pubkey}>
            <div className='p-5 bg-gray-800 rounded-3xl overflow-x-clip'>
                <div className='overflow-x-clip'>
                    <div className='block'>
                        <div className="flex mb-5">
                            <UserProfile size={80} profile={user.profile} displayName={user.displayName} /> 
                            <div className='group px-5'>
                                <h3 className='text-[28px] lg:text-[28px] text-left mt-3 text-gray-400 font-bold'>
                                    {user.displayName}
                                </h3>
                            </div>
                        </div>
                        
                        {user.about &&
                            <div className="w-full pt-1">
                                <label className="text-gray-200 font-bold text-[12px]">
                                    {user.about}
                                </label>
                            </div>
                        }

                        <div className='py-2'>
                            <button 
                                onClick={() => copyToClipboard(user.pubkey)}
                                className='w-full text-center text-gray-200 text-[12px] bg-[#3e2eb3] p-2 px-5 rounded-[10px]'>
                                {hexToNpub(user.pubkey).substring(0, 38)}..
                                <AiOutlineCopy className="text-gray-200 m-1 mx-2 text-[14px] float-end" />
                            </button>
                        </div>

                        <p className='text-gray-500 text-[12px] font-bold'>Similarity: {user.similarity}</p>
                    </div>
                </div>
            </div>
        </div>
    )
}

type UserListProps = {
    users: User[]
}

export const UserList = ({ users }: UserListProps) => {
    return (
        <div className='w-full grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4 md:gap-7 py-5 md:py-8 px-3 md:px-6'>
            { users.length &&
                users.map(user => <UserItem key={user.pubkey}user={user} />)
            }
        </div>
    )
}
