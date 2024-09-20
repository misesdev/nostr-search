import Image from 'next/image';
import Link from 'next/link';
import SearchBox from './SearchBox';
import { RiSettings3Line } from 'react-icons/ri';
import { TbGridDots } from 'react-icons/tb';
import SearchHeaderOptions from './SearchHeaderOptions';

export default function SearchHeader() {
    return (
        <header className='top-0 bg-gray-800'>
            <div className='lg:flex w-full p-4 lg:p-6'>
                <div className='hidden lg:flex'>
                    <Link href='/'>
                        <Image
                            src='/logo.png'
                            alt='Nostr Book Users'
                            width={40}
                            height={40}
                            priority
                            style={{ width: 'auto' }}
                        />
                    </Link>
                </div>
                <div className='lg:hidden w-full mb-4 flex px-2'>
                    <Link href='/'>
                        <div className='flex'>
                            {/* <Link href='/'> */}
                                <Image
                                    src='/logo.png'
                                    alt='Nostr Book Users'
                                    width={32}
                                    height={32}
                                    priority
                                    style={{ width: 'auto' }}
                                />
                            {/* </Link> */}
                            <h3 className='text-[16px] font-bold mt-1 ml-5 text-gray-400'>Nosbook</h3>
                        </div>
                    </Link>
                    <div className='flex-1'>
                        <button className='bg-[#3e2eb3] float-end text-[12px] text-gray-300 py-2 px-5 rounded-md hover:brightness-105 hover:shadow-md transition-shadow ml-2'>
                            Sign in
                        </button>
                    </div>
                </div>
                <div className='flex-1'>
                    <SearchBox />
                </div>
                <div className='hidden lg:flex'>
                    {/* <div className='hidden md:inline-flex space-x-2'> */}
                    {/*     <RiSettings3Line className='bg-transparent hover:bg-gray-200 p-2 text-4xl rounded-full cursor-pointer' /> */}
                    {/*     <TbGridDots className='bg-transparent hover:bg-gray-200 p-2 text-4xl rounded-full cursor-pointer' /> */}
                    {/* </div> */}
                    <button className='bg-[#3e2eb3] text-gray-300 px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow ml-2'>
                        Sign in
                    </button>
                </div>
            </div>
            <SearchHeaderOptions />
        </header>
    );
}
