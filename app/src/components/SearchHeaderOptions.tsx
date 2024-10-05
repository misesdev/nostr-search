'use client';

import { defaultPubkey } from '@/constants';
import { usePathname, useRouter, useSearchParams } from 'next/navigation';
import { ReactNode, useEffect, useState } from 'react';
import { AiOutlineCamera, AiOutlineSearch } from 'react-icons/ai';

export default function SearchHeaderOptions(): ReactNode {
    
    const router = useRouter();
    const pathname = usePathname();
    const searchParams = useSearchParams();
    const searchTerm = searchParams.get('searchTerm');

    const [pubkey, setPubkey] = useState(defaultPubkey);

    useEffect(() => {
        const pubkey = searchParams.get('pubkey');
        
        if(pubkey) setPubkey(pubkey)
    }, [searchParams])
    
    const selectTab = (tab: string) => {
        router.push(`/search/${tab}?searchTerm=${searchTerm}&pubkey=${pubkey}`)
    }
    
    return (
        <div className='flex space-x-2 select-none w-full justify-start pl-10 text-gray-700 text-sm'>
            <div onClick={()=>selectTab("web")} className={`text-gray-200 flex items-center space-x-1 border-b-4 border-transparent active:text-blue-500 cursor-pointer pb-3 px-2 ${pathname === '/search/web' && '!text-blue-600 !border-blue-600'}`}>
                <AiOutlineSearch className='text-md' />
                <p>Profile</p>
            </div>
            <div onClick={()=>selectTab("image")} className={`text-gray-200 flex items-center space-x-1 border-b-4 border-transparent active:text-blue-500 cursor-pointer pb-3 px-2 ${pathname === '/search/image' && '!text-blue-600 !border-blue-600'}`}>
                <AiOutlineCamera className='text-md' />
                <p>Images</p>
            </div>
            <div onClick={()=>selectTab("relays")} className={`text-gray-200 flex items-center space-x-1 border-b-4 border-transparent active:text-blue-500 cursor-pointer pb-3 px-2 ${pathname === '/search/relays' && '!text-blue-600 !border-blue-600'}`}>
                <AiOutlineCamera className='text-md' />
                <p>Relays</p>
            </div>
        </div>
    );
}



