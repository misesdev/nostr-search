import { ReactNode } from "react";

const HomeHeader = (): ReactNode => {
    return (
        <header className='flex justify-end p-5 text-sm'>
            <div className="flex space-x-4 items-center">
                <button className='bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow'>Sign in</button>
            </div>
        </header>
    )
}

export default HomeHeader
