import Image from 'next/image';
import Link from 'next/link';
import SearchBox from './SearchBox';
import { RiSettings3Line } from 'react-icons/ri';
import { TbGridDots } from 'react-icons/tb';
import SearchHeaderOptions from './SearchHeaderOptions';

export default function SearchHeader() {
    return (
        <header className='bg-gray-800 sticky top-0'>
            <div className='flex w-full p-6 items-center justify-between'>
                <Link href='/'>
                    <Image
                        src='/logo.png'
                        alt='Nostr Book Users'
                        width={50}
                        height={50}
                        priority
                        style={{ width: 'auto' }}
                    />
                </Link>
                <div className='flex-1'>
                    <SearchBox />
                </div>
                {/* <div className='hidden md:inline-flex space-x-2'> */}
                {/*     <RiSettings3Line className='bg-transparent hover:bg-gray-200 p-2 text-4xl rounded-full cursor-pointer' /> */}
                {/*     <TbGridDots className='bg-transparent hover:bg-gray-200 p-2 text-4xl rounded-full cursor-pointer' /> */}
                {/* </div> */}
                <button className='bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow'>
                    API Docs
                </button>
            </div>
            <SearchHeaderOptions />
        </header>
    );
}
