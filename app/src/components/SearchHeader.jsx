import Image from 'next/image';
import Link from 'next/link';
import SearchBox from './SearchBox';
import { RiSettings3Line } from 'react-icons/ri';
import { TbGridDots } from 'react-icons/tb';
import SearchHeaderOptions from './SearchHeaderOptions';

export default function SearchHeader() {
    return (
        <header className='sticky top-0 bg-gray-800'>
            <div className='flex w-full p-6 items-center justify-between'>
                <Link href='/'>
                    <Image
                        src='/logo.png'
                        alt='Google Logo'
                        width={60}
                        height={40}
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
                <button className='bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow ml-2'>
                    Sign in
                </button>
            </div>
            <SearchHeaderOptions />
        </header>
    );
}
